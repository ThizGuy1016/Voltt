#include "tok.hpp"

namespace Voltt {
namespace Tok {

auto dump(std::ostream& _os, const Token& _tok, const char* _source) -> void
{
	const char* word = to_str(_tok, _source);
	_os << "Token {\n";
	_os << "  word: " << word << '\n';
	_os << "  offset: " << _tok.offset << '\n';
	_os << "  end: " << _tok.end << '\n';
	_os << "  line: " << _tok.line+1 << '\n';
	_os << "  col: " << _tok.col << '\n';
	_os << "}\n";

	// safely deallocates memory
	switch (_tok.id) {
		case ALLOC_STR_CASE: std::free((void*)word);
		default: return;
	}
}

auto dump_errctx(const Tok::Token& _tok, const char* _source, const char* _fname) -> Logger::CompCtx_t
{
	size_t line_start = _tok.offset;
	size_t line_end = _tok.end;

	for (;;) if (line_start <= 0 || _source[--line_start] == '\n') break;

	for (;;) if (line_end >= strlen(_source) || _source[++line_end] == '\n') break;

	return Logger::CompCtx_t{
		.m_start = _tok.offset,
		.m_end = _tok.end,
		.m_line_start = line_start,
		.m_line_end = line_end,
		.m_line = _tok.line,
		.m_fname = _fname,
		.m_fd_contents = _source,
	};
}

auto to_str(const Tok::Token& _tok, const char* _source) -> char const*
{
	switch(_tok.id) {
		default: 
			Logger::debug(
				Logger::DBCTX,
				Logger::DebugErrID::DebugErrID_t::TOKID_STR_ERR,
				std::string{"Unable to convert: "}+std::to_string(_tok.id)+" to str."
			);
	
		case TokenColonSymbol: return ":";
		case TokenColonInferMut: return ":=";
		case TokenColonInferConst: return "::";
		case TokenEqSymbol: return "=";

		case TokenCmpGreater: return ">";
		case TokenCmpGreaterEq: return ">=";
		case TokenCmpLess: return "<";
		case TokenCmpLessEq: return "<=";

		case TokenArrowRight: return "->";
		case TokenArrowLeft: return "<-";

		case TokenComma: return ",";

		case TokenParenOpen: return "(";
		case TokenParenClose: return ")";

		case TokenBracketOpen: return "{";
		case TokenBracketClose: return "}";	

		case TokenBinOpAdd: return "+";
		case TokenBinOpSub: return "-";
		case TokenBinOpMul: return "*";
		case TokenBinOpDiv: return "/";

		case TokenTypS32: return "s32";

		case TokenFn: return "fn";
		
		case TokenEndStatement: return "TokenEndStatement";
		case TokenEndOfFile: return "TokenEndOfFile";

		// In order to prevent memory leaks the result of this function must follow this pattern
		// switch (Tok::Token.id) {
		//	  case Tok::ALLOC_STR_CASE: std::free((char*)word);
		//	  default break;
		// }
		// This solution is hacky, but it can greatly reduce the amount of allocations and copies.
		// Look into defer.hpp for nicer looking ways to clean up	

		case ALLOC_STR_CASE:
			size_t len = (_tok.end-_tok.offset)+1;
			char* result = (char*)std::malloc(len);
			std::memcpy(result, &_source[_tok.offset], len);
			result[len] = 0;
			return result;
	}
	Logger::unreachable_err();
}

} // namespace Tok
} // namespace Voltt
