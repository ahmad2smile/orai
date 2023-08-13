//
// Created by ahmad on 8/13/23.
//

#ifndef ORAI_STATEMENT_H
#define ORAI_STATEMENT_H

namespace Orai {

    class Statement {
    private:
        const char *raw;

    public:
        explicit Statement(const char *raw);

        void Debug();
    };

} // Orai

#endif //ORAI_STATEMENT_H
